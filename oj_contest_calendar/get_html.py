from selenium import webdriver
from selenium.webdriver.chrome.options import Options
# import io
import sys
import time

def get_html(url, file_name, driver) :
  driver.set_window_size(2000,2000)
  driver.get(url)
  # driver.execute_script("var q=document.documentElement.scrollTop=10000")
  for i in range(10):
    driver.execute_script(f'document.documentElement.scrollTop={(i+1)*1000}')
  time.sleep(1)
  f = open(file_name, 'w', encoding='utf-8')
  f.write(driver.page_source)
  f.close()

# sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='gb18030')
# # print("Hello World")
# # from selenium import webdriver
# driver = webdriver.Chrome()
# url = 'https://www.luogu.com.cn/contest/list'
# driver.get(url)
# # driver.maximize_window()
# f = open('luogu.html', 'w', encoding='utf-8')
# # print(driver.page_source)
# # print(type(driver.page_source))
# f.write(driver.page_source)
# # f.write("1231564")
# f.close()

chrome_options = Options()
chrome_options.add_argument("--headless")  # 添加参数以隐藏浏览器窗口
driver = webdriver.Chrome(options=chrome_options)
# 'https://www.luogu.com.cn/contest/list'
# 'luogu.html'
get_html(sys.argv[1], sys.argv[2], driver)

# D:/Program/anaconda4/python.exe test.py https://www.luogu.com.cn/contest/list luogu.html