# 源码库同步

这是暂定方案，如有更方便的方法，随时更新。 教师之间推荐完整同步方法，也可以像学生一样使用学生目录法。

## 1. 源码库结构

做软件可以是一件比较有趣的事，教科书里的标准源码目录比较无趣，我的目录名字跟通用做法不一样。
因此，特别在这里说清楚，将来诸位也需要跟自己的学生说清楚。

这是目前的总目录：

* `cpp`: C++ 课程源码。

* `python`: Python 课程源码。

* `racket`: Racket
  课程源码。**这是我自己的私有课程，放在这里是方便诸位自行学习，假如课程源码需申请专利，届时应当移走该目录的内容。**
  此外，此目录下也包含这篇手册的源码。这可以作为例子告诉学生，编程和写作是同类活动；即使将来只想做作家，懂编程也将如虎添翼。

* `mascot`: 课程素材，主要是图片。所有语言通用。

对照图1.1，每个课程的源码按如下目录组织（先把课程假想成软件，再把软件假想成数字生物，这样会更容易理解）。

* _._: 源码根目录，相当于常规的 `src`，存放最直接的源码，包括带 _main_ 的程序入口文件、
  你愿意共享给别人使用的模块文件和头文件。软件一旦发布，你修改这些文件必须保证兼容性，或以较为正式的方式告知别人为什么要放弃兼容性。
  顺便说一句，用我自己的构建工具编译 C++ 项目，可以存在多个 _main_，一般一个 _main_ 代表一个程序。

* _digitama_: 私有源码目录，表示这个目录里的源码不对外开放。你修改这些文件无需保证兼容性，
  如果别人非要直接使用这些源码，后果自负。比如因你修改源码而导致他们程序崩溃，他们怨不得你。 `digitama`
  是“数码蛋”的意思，意为我们的软件是从这个蛋里孵出来的。

* _stone_: 资源目录，相当于常规的 `res` 或 `Assets`，存放资源和(静态)配置信息，
  比如图片素材、界面文字的多语言翻译等。`stone` 源自“罗赛塔石碑(Rosetta
  Stone)”，石碑上刻着对于任务而言至关重要的信息， 这些信息只可读不可写。

* _tamer_: 测试目录，是常规的 `tests` 和 `docs` 的结合，用于存放测试程序和项目文档。
  这个更像是我的个人偏好，项目文档应当与软件的实际运行情况一致，因此一种做法是把文档以注释的形式写在源码里，
  但对于大项目仅仅因为修改了注释就要重新编译整个项目，这想想都不划算(大项目的编译相当耗费时间)。
  于是，我喜欢将文档和测试结合，这样我提供的文档，既包含了函数签名，还包含用法举例，以及算法的正确性验证等信息。
  `tamer`是“驯兽师”的意思，寓意明显。

* _literacy_: 出版物源码目录。这也是我的个人偏好，在软件项目里没有对应的标准目录。相对于上面提到的项目文档，
  这个目录里面的内容要正式一些，作品可能是一本书、一篇论文等，以 pdf (而非网页)形式提供，比如你现在正在读的这份手册。
  `literacy` 就是字面意思“文字能力”，无寓意。

* _village_: 协作目录，相当于开源项目的 `contrib`。总体上说，这个目录里面的东西比较包罗万象。
  比如，你的软件用到了其他软件、你想编写额外代码以支持其他软件、别人与你协作开发并扩展了你的软件， 这些源码（或二进制文件）都可以放在这里。
  `village` 源自“创始村(Primary Village)”，数码宝贝出生的地方。

  在本系列课程中，其他类型的课程代码也放在这里了。比如

  * `STEMA`: STEM 能力测试赛题源码。学生考前冲刺用的，也可作为非比赛学生夯实基本功的作业题。

  * `sketch`: 草稿源码，每个文件都自带 main，用于演示语言的某一个细节。比如众所周知的 `"Hello, World!"`。
    这是个特殊的目录，`basis`肯定会用到，其他课可能会用到，可以现场发给学生，也可以把源码包含在课件里。

  * `procedural`: 过程式风格示例源码。过程式风格更为注重细节，复杂度未必有多大，但代码量多半会让初学者生畏。
    因此仅作为对比材料发放给学生，学生根据自身情况课后自行决定是否掌握。

  * `vcso`: 适用于 vcpkg 的 Windows 动态链接库，是二进制文件。有这个目录学生就不必自己安装了，
    详细信息见\[missing\]

以上条目未必都会出现在同一课程目录里，如果出现，一定符合上述解释。比如 `literacy` 就只出现在 `racket`
里，手册只需写一份就行。

\#<pict>
**图 1.1. **源码目录结构

此外，还有两个特殊文件(夹)，文件名不可更改。

* _info.rkt_: Racket 软件包的元信息文件。用来配置我的 C++ 构建工具，比如哪些文件需要编译，怎么编译等。

* _compiled_: Racket 编译缓存目录，用于存放所有编译过程中可以自动生成的文件。注意，此目录不唯一，
  各个被编译的文件所在的目录里都有一个。

  以下几个子目录在我们的课程中也可能用到：

  * _typesetting_: 存放 literacy的输出，比如本手册
    `"compiled/typesettings/YouLanguage.pdf"`。

  * _native_: 存放 C++ 二进制文件的输出，比如
    `"compiled/native/win32/x86_64/BigBang"`。
    注意，它这里面会根据体系结构和操作系统划分子目录。

`compiled` 和 Python 源码目录里的 `__pycache__` 功能相同。

此外，Python 目录本身也有一系列约定俗成的规则，但目前我们的课程不会涉及相关概念，暂且不表。

## 2. 完整同步

本系列所有课程的源码都组织在一个版本库(repository)里，其中共享源码(也就是前文一再提及的“配套的软件库”)以子库(submodule)的形式独立存在，以方便单独共享，
比如我自己的项目也会用到它。于是，初次同步，先选一个用于存放源码的目录，比如 `"G:\Laboratory"`，然后打开 PowerShell
执行以下命令：

*   `cd G:\Laboratory\YouthLanguage`

*   `git clone --recurse-submodules
  https://github.com/Gyoudmon/YouthLanguage.git .`

*   `git submodule foreach git checkout master`

第三步很重要，要不然拉过来的子库源码不属于任何分支，这是 git submodule 经常被人诟病的地方。 以后需要更新时，只需

*   `cd G:\Laboratory\YouthLanguage`

*   `git pull`

*   `git submodule foreach git pull`

建议大家平时学一下 git 的基本用法，避免不小心修改了拉回来的代码，导致下次 `pull` 时冲突没法正常同步。 如果真碰到这事了，又嫌学
git 麻烦，那就删掉这个文件夹，从头开始重新 `clone`。

## 3. C++ 代码的编译和运行

在开发软件的过程中，打开 PowerShell 并且 `cd` 到当前项目目录是个好习惯。 在本系列课程中，一般就是指 info.rkt
文件所在的目录。 如果涉及多个项目，每个项目单独开一个 PowerShell 比较合理，不用来回切换了。 如果使用 Visual Studio
Code，也可以直接启动它的终端， 不过那个终端是 `cmd.exe` 而非 PowerShell，虽说在编译这件事上差别不大。
这样可以以假乱真，假装是在用 IDE。

对于 `sketch` 这种草稿性质的代码，一般不需要特别复杂的编译参数，可以直接编译

*   `raco wisemon -d cc [入口文件.cpp]`

其中，`raco` 是 Racket 提供的命令行；`wisemon` 是我的构建工具； `---d`
表示输出编译过程，但不要太啰嗦；`cc`是 C/C++ 编译器（C Compiler）的首字母缩写。

对于 `basis` 这样的复杂项目，编译参数通常都会很复杂，因为我会在 `"info.rkt"` 里配置好，然后直接编译

*   `raco wisemon -d cc`

这次连入口文件都不用指定，它会自己解析 info.rkt 文件找到要编译的文件，并设置好相应的参数。
无论用哪种方式，编译完了之后的可执行文件，都在与入口文件相同目录的 `"compiled/native"` 子目录里。 比如，
`cpp/basis` 课程目录中有个 `"FontBrowser.cpp"` 文件，它已被配置在 info.rkt 中。
于是，它对应的可执行文件名是`"cpp/basis/compiled/native/win32/x86_64/FontBrowser.exe"`。

Python 源码不需要编译，直接运行与 C++ 入口文件名相同的文件即可。

## 4. 学生目录

一般来说，不建议学生直接修改教师的源码，学生应该另外找一个目录，保持目录结构不变，创建好自己的课程目录。
比如`"G:\Course\YouthLanguage\cpp"`，然后把教师目录下的`"info.rkt"`
和已经配置好的入口文件复制到该目录下，最后单独`clone`配套的源码库和素材库：

*   `git clone https://github.com/Gyoudmon/big-bang.cpp.git
  G:\Course\YouthLanguage\cpp\digitama\big_bang`

*   `git clone https://github.com/Gyoudmon/mascot.git
  G:\Course\YouthLanguage\mascot`

使用 Windows 的学生还需要再同步一个`vcso.git`，有这个就不用另外安装 vcpkg
了（就是那个可以跳过的\[missing\]）。 使用其他操作系统的学生无需同步这个共享库。

*   `git clone https://github.com/Gyoudmon/vcso.git
  G:\Course\YouthLanguage\cpp\village\vcso`

Python 学生将其中的 `big-bang.cpp.git` 替换成 `big-bang.py.git` 即可，也不需要
`vcso.git`：

*   `git clone https://github.com/Gyoudmon/big-bang.py.git
  G:\Course\YouthLanguage\python\digitama\big_bang`

*   `git clone https://github.com/Gyoudmon/mascot.git
  G:\Course\YouthLanguage\mascot`
