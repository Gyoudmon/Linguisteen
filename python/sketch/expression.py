#!/usr/bin/env python3

import sys # 系统相关参数和函数

################################################################################
def main(argc, argv):
    coding_age = 2  # 定义一个变量并赋值为整数 2，因此这是一个 int 型变量
    print("假如你已经学了 " + str(coding_age) + " 年编程。")

    # 注意：跟在数学中的意义不同，"=" 在程序语言中一般表示“赋值”, 而非“两边相等”
    coding_age = coding_age + 3
    print("那么，再过三年，你就已经学了 " + str(coding_age) + " 年编程啦！")

    return 0



################################################################################
if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))

