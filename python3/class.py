#! /usr/bin/env python3

from threading import Thread, Lock
import time

def print_time(threadName, delay):
    count = 0
    while count < 5:
        print('{}: {}'.format(threadName, time.ctime()))
        count += 1
        time.sleep(delay)


class myThread(Thread):
    def __init__(self, threadID, name, counter):
        Thread.__init__(self,)
        self.threadid = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print('开始线程: {}'.format(self.name))
        threadLock.acquire()
        print_time(self.name, self.counter)
        threadLock.release()


threadLock = Lock()


mt = myThread(1, 'thread_1', 3)
mt.start()
mt.is_alive()

athr = Thread(target=print_time, args=('python_2', 3))
athr.start()
mt.join()
print('线程退出')