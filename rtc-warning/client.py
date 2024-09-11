from slack_sdk import WebClient
from slack_sdk.errors import SlackApiError
import datetime
import schedule
import time
from configparser import ConfigParser
import logging 
import os

global_last_result = []
global_apptoken = ""
global_check_interval = 10
global_botroom_check_interval = 3600
global_warning_channelid = []
global_targetroom_channelid = ''
global_im_keyword = []
logger = logging.getLogger('my_logger')
global_lasttime_warning = []

global_checktime_statistic = 0;
class KeywordCheck:
    # 初始化方法，当创建新的实例时自动调用
    def __init__(self, channelid):
        self.channelid = channelid  # 实例变量
        self.checkResult = []
    def tsConversion(self,ts):
        int_part, decimal_part = ts.split('.')
        dt_object = datetime.datetime.fromtimestamp(int(int_part))
        time_str = dt_object.strftime('%Y-%m-%d %H:%M:%S')
        return time_str
    def checkKeyword(self):
        client = WebClient(token=global_apptoken)
        response = client.conversations_info(channel = self.channelid)
        channel = response['channel']
        print(f"Channel Name: {channel['name']}")

        conversation_history = []
        try:
            current_timestamp = int(time.time())
            print("当前Unix时间戳:", int(current_timestamp))
            old_timestamp = current_timestamp - 60 * 10

            result = client.conversations_history(channel = self.channelid,oldest=old_timestamp, latest=current_timestamp)
            conversation_history = result["messages"]
            for item in conversation_history:
                 for keyitem in global_im_keyword:
                    if( keyitem in item["text"]):
                        ret = channel['name']+"-"+self.tsConversion(item["ts"]) +",text:" +  item["text"]
                        print(ret)
                        self.checkResult.append(ret)
        except SlackApiError as e:
            print("Error creating conversation: {}".format(e))
        return self.checkResult;

class Util:
    def __init__(self):
        self.checkResult = []
    def timed_function(self):
        global global_checktime_statistic

        global_checktime_statistic += 1
        if(global_checktime_statistic * global_check_interval >  global_botroom_check_interval):
            util.read_config(1);
            global_checktime_statistic = 0;

        util = Util();
        util.read_config(0);
        global global_last_result
        cur_result =[]
        for item in global_warning_channelid:
            check = KeywordCheck(item)  
            ret = check.checkKeyword()
            for inner in ret:
                cur_result.append(inner);

        for item in cur_result:
            print("timed_function conversation:" + item)
        
        if(len(global_last_result) == 0):
            global_last_result = global_lasttime_warning
        difference = [item for item in cur_result if item not in global_last_result]   

        for item in difference:
            print("timed_function diff:" + item)
            # 用你的Slack OAuth Token替换
            client = WebClient(token=global_apptoken)
            try:
                response = client.chat_postMessage(
                    channel = global_targetroom_channelid,  # 频道ID或名称
                    text = item
                )
                logger.debug(item)
                print(f"Message sent: {response['message']['text']}")
            except SlackApiError as e:
                print(f"Error sending message: {e.response['error']}")
                
        global_last_result = cur_result

    def read_config(self,botroom_check):
        global global_apptoken
        global global_im_keyword
        global global_warning_channelid
        global global_targetroom_channelid
        global global_check_interval
        global global_botroom_check_interval
        config = ConfigParser()
        try:
            config.read(os.getcwd() + '/config.ini')
            print(config.sections())
        except SlackApiError as e:
                print("Error creating conversation: {}".format(e))
        # 获取数组
        global_apptoken = config['app_token']['token']
        #global_warning_channelid = [(item) for item in config['warning_channenlid']['array'].split(',')]
        global_im_keyword = [(item) for item in config['rtc_keyword']['array'].split(',')]
        global_targetroom_channelid = config['target_channelid']['array']
        global_check_interval = int(config['check_interval']['array'])
        global_botroom_check_interval = int(config['botroom_check_interval']['array'])

        if(botroom_check):
            self.get_monitor_channelid();
        
    def initLog(self):
        logging.basicConfig(level=logging.DEBUG,
                        format='%(asctime)s - %(levelname)s - %(message)s',
                        datefmt='%Y-%m-%d %H:%M:%S',
                        filename='app.log',
                        filemode='w')
        logger.setLevel(logging.DEBUG)
        # 创建一个文件日志处理器
        fh = logging.FileHandler(os.getcwd() + '/rtc_warning.log')
        fh.setLevel(logging.DEBUG)

        # 创建一个流日志处理器（控制台输出）
        ch = logging.StreamHandler()
        ch.setLevel(logging.DEBUG)

        # 创建一个日志格式
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

        # 设置文件和流处理器的格式
        fh.setFormatter(formatter)
        ch.setFormatter(formatter)

        # 添加文件和流处理器到日志记录器
        logger.addHandler(fh)
        logger.addHandler(ch)
        logger.debug('rtc warning started')
    def get_lasttime_warning(self):
        client = WebClient(token=global_apptoken)
        conversation_history = []
        try:
            result = client.conversations_history(channel = global_targetroom_channelid)
            conversation_history = result["messages"]
            for item in conversation_history:
                global_lasttime_warning.append(item["text"])
        except SlackApiError as e:
            print("Error creating conversation: {}".format(e))

    def get_monitor_channelid( self,cursor=None):
        client = WebClient(token=global_apptoken)
        try:
            response = "";
            if(cursor == None):
                response = client.conversations_list(
                types="private_channel",
                limit=1000)
            else:
                response = client.conversations_list(
                types="private_channel",
                limit=1000,
                cursor=cursor)
            channels = response.get("channels", [])
            next_cursor = response.get("response_metadata", {}).get("next_cursor")

            # 处理当前页的频道
            for channel in channels:
                if channel['is_private'] and channel['id'] not in global_targetroom_channelid:
                    global_warning_channelid.append(channel['id'])
                    print(f"Channel ID: {channel['id']}, Name: {channel['name']},Name: {channel['is_private']}")

            # 如果有下一页，则递归调用
            if next_cursor:
                return self.fetch_conversations(next_cursor)
        except SlackApiError as e:
            print(f"Error fetching conversations: {e}")


if __name__ == "__main__":
    util = Util();
    util.initLog();
    util.read_config(1);
    util.get_lasttime_warning();
    schedule.every(global_check_interval).seconds.do(util.timed_function)
    
    while True:
        schedule.run_pending()
        time.sleep(1)
