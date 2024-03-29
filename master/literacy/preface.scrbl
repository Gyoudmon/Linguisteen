#lang scribble/manual

@(require "literacy.rkt")

@handbook-root-story{理念与思路}

青少年计算机科学课面向的学生群体是小学生和中学生，
因此在课程研发策略上讲究能够向下兼容的@tech{自顶向下}设计。
简单来说，单从内容上看，要能满足最高级学生的需要，
而具体的教学实施由各教师根据自己的风格和学生特点来取舍，
授课内容不用面面俱到，但教师的知识储备不能成为学生升阶的天花板。

从学生接受能力的角度看，@tamer-deftech{自顶向下}设计的优势是，
能与生活经验、已学知识建立连接、形成知识网络。
在教学实施过程中，教师应当注重引导学生发现生活经验中的计算思维。
举个简单例子，对着墙壁抛出皮球，球碰到墙壁会反弹。
现用软件模拟这个过程，有 Scratch 经验的学生已经知道，
只需拖动一个叫做“碰到边界反弹”的积木到角色的代码区；
那这个操作在 C++/Python 中也应该简化为一行代码：
比如@id{set_border_strategy(BOUNCE)}。
学习 Scratch 的学生不关心“碰到边界反弹”的积木是怎么实现的，
那他们在初学 C++/Python 时也不需要深究算法如何判断边界、如何控制反弹。
普通学生可以在后续课程中逐渐深入，学有余力的学生也可以自己研读配套的代码库。

编程中的概念很抽象，即使是大学生也未必能一次就学会，一开始“听不懂”才是正常现象。
因此，教师必须要先帮助初学者建立好正确的心理预期。
这是教学实施方面的细节，教师应该自主探索最适合自己和学生的方法。
