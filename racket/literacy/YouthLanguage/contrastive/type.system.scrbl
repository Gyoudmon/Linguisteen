#lang scribble/manual

@(require "../../literacy.rkt")

@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@handbook-root-story{类型与类型系统}

@tamer-deftech{类型}决定了软件作者和机器如何解读变量的值。
比如，看到@litchar{60}，我们大多数人会默认它是个数字，
但公交车司机就很可能把它解读成公交车编号，即@litchar{60路公交车}。
也就是说，如果不事先商量好，那就真有可能造成“一千个读者一千个哈姆雷特”式混乱。
日常交流这不是问题，但在真正需要解决问题时，
就必须要消除这种混乱(最起码要能达成共识)。
一个总是跟你吵架的软件没有存在价值。

于是，@idea{用类型思考问题}是所有编程初学者的基础训练目标。
继续上面的例子，如果把@litchar{60}解读成整数，
那它可以参与算术运算 @${60 * 2 = 120}(数值类型有数量关系)；
但如果解读成公交车编号，
它参与算术运算就没有意义(60路公交和120路公交没有任何数量关系)，
不过在具体的应用中我们仍有可能给它定义其他有意义的运算，
比如@question{将多辆60路公交编组成一队}，
以参与完成一次救援任务。

@tamer-deftech{类型系统}则是指程序语言提供的一种机制，
这种机制可以用来帮助软件作者声明值的类型，
并提供一定的@tamer-deftech{类型检查}机制以确保程序的类型安全，
进而@focus{确保软件能正常且正确地运行}。
@tech{类型系统}作为一个重要且基础的方面，
可用于区分不同的语言。即，当你学习新语言时，
@tech{类型系统}的差异是你需要着重关注的点。
另外，确保软件正常且正确的途径有很多，
@tech{类型系统}只是其中的一种，属于语言层面的保障。
其他层面有其他手段，不在这里讨论。

@handbook-scenario{编译期类型检查}

@handbook-scenario{运行期类型检查}

@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@handbook-reference[]
