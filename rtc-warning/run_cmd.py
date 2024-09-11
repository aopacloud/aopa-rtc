import multiprocessing
import time

def worker():
    while True:
        print("守护进程正在运行...")
        time.sleep(1)

if __name__ == '__main__':
    # 创建一个进程对象
    p = multiprocessing.Process(target=worker)
    # 将进程设置为守护进程
    p.daemon = True
    # 启动进程
    p.start()
    # 等待用户输入，然后结束主进程
    input("按下回车键退出程序...")
    p.terminate()  # 终止守护进程
    p.join()       # 等待守护进程结束