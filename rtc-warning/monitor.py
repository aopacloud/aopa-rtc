import subprocess
import time
import multiprocessing
import os
def run_daemon():
    # 启动守护进程
    cmdPath = os.getcwd() + '/client.py'
    process = subprocess.Popen(['python3', cmdPath])
    return process

def monitor_daemon():
    while True:
        process = run_daemon()
        process.wait()  # 等待进程结束
        print("Daemon stopped, restarting...")
        time.sleep(10)  # 等待一段时间再重启

if __name__ == "__main__":
    #monitor_daemon()
    p = multiprocessing.Process(target=monitor_daemon)
    p.start()
    time.sleep(5)  # 等待一段时间再重启
    p.join()       # 等待守护进程结束
    #os._exit(0)