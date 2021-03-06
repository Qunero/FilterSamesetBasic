1、FilterSamesetBasic的组织形式：
FilterSamesetBasic  # 项目最上层目录
├── CMakeLists.txt  # 整个项目的cmake配置文件
├── FilterSamesetBasic.pro  # 整个项目的qmake的配置文件
├── doc             # 文档目录
│   └── difference_between_stlList_and_QList.txt # 讲述STL list和QList的文件
├── src             # 源代码目录
│   ├── CMakeLists.txt  # 源代码处理的cmake配置文件 
│   ├── main.cpp        # 主程序cpp文件
│   ├── mainwidget.cpp  # 主窗口cpp文件
│   └── mainwidget.h    # 主窗口头文件
└── ui                  # 该项目的ui存放目录
    └── mainwidget.ui   # 主窗口的ui文件 

2、本项目可以通过3种形式实现编译和运行：
2.1 使用qtcreator自动构建：
    导入该项目，设置好构建路径（也可以打开项目后在左侧导航栏的“项目”面板进行设置）；
    通过“构建”菜单的下拉菜单“运行”快速完成构建和运行，也可以通过相应快捷键如alt+r实现；

2.2 命令行通过qmake构建：
    进入项目文件夹，建立构建专用目录build并进入：
        mkdir build; cd build
    重新生成pro文件或者对其做必要的修改，或者直接使用已经设置好的FilterSamesetBasic.pro;
    运行qmake， 生成相应的Makefile:
        qmake ../FilterSamesetBasic.pro 
    运行make，生成相应的可执行程序FilterSamesetBasic
        make 

2.3 命令行通过cmake构建：
    当前已经在主目录生成CMakeLists.txt文件，对应子目录的文件和内容也已经设置好，可以直接使用，
    在项目的祝目录下新建构建专用目录cmake_build, 并进入 ：
        mkdir cmake_build; cd cmake_build
    在cmake_build目录中运行cmake生成相应的Makefile
        cmake ../ 
    生成Makefile后运行make进行编译：
        make
    最后生成的可执行程序放在编译目录下的bin目录里，可以运行进行使用：
        bin/FilterSamesetBasic 

3、参考资料和网址：
Qt开发书籍  ：  《G++ GUI Qt4编程》
STL必备书籍 ：  《C++标准程序库--自修教程与参考手册》
Cjacker的cmake实践  ：  《Cmake 实践》
C++在线API和实例    ：  http://www.cplusplus.com/reference/
qt官方在线文档      ：  http://qt-project.org/doc/
git详解系列教程     ：  http://www.open-open.com/lib/list/282
cmake qt配置精要    ：  http://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects

4、项目设计和说明：
4.1 关于ui
    在ui上有一点很小的修改，添加了一个reset按钮，用于清除已选的文件路径；整体会更加美观和实用
一些，也方便测试；这里绝对不是不尊重原始设计，如果是实际项目肯定会按相关文档设计和处理，然后有
具体的建议会积极提出来讨论，确实不错再去实现；这里由于一开始就加进去了，所以没有删除相关ui控件和
代码，其实现在的ui看起来也不错哈；
    实践过程使用qt的设计助手做的ui，完全写代码实现也可以，但是就显得代码不够精简了；所以选择了
前者，在实际过程中也加入了一些思考，比如界面缩放，如果高度太高则显得很难看，所以做了最大高度的
限制，保证缩放过程中整体效果一致；另外对process按钮默认做了disable的处理，设计了相应的简单的
信号槽以实现选择了文件后该按钮才可用；并且处理完成后又设置为不可用，防止多次点击将原始文件覆盖；
4.2 关于逻辑和算法
    整体运行逻辑如下：选择2个文件，显示相应路径，文件都选好后可以开始点击process处理，删除某一
文件路径后或者reset后该按钮处于不可用状态，（TODO：文件路径变化后，检查相应文件是否存在，然后
确定该按钮是否可用，当前只简单检查路径是否为空）；点击处理后， 先做文件备份，如果存在则先删除源
来的备份文件保证本次备份成功（TODO:更多的异常和备份失败等的处理）；文件备份后读取备份文件写入到
原来名字的文件；
    文件去重复算法为：读取其中一个文件，存取每一行到hash中，每个节点为一个结构体保存2个信息，
一是该行出现的次数，另一个是该行是否为两文件共有的（存结构体是为了防止重复的行多次存储，以节省
内存；这里主要考虑两个文件去重，但是同一个文件内部可能有重复但是保留，否则不用存结构体，只需存
储是否为共有的，程序可进一步简化）；读取完一个文件并存储后，开始读取并处理另一个文件，检查每一行
是否另一个文件有，若有则不输出该行，并将hash中相应位置的标记设为true，这样可以直接处理完第二个文
件；最后遍历hash，将不是两个文件共有的内容输出到第一个文件相应的位置；（TODO：如果文件较大，则
可以先将2个文件比较大小，先读小文件并存储，后直接读取和写出较大的那个文件，从而降低资源消耗；另
一种策略，将较大的两个文件先调用外部排序工具排序，然后采用动态比较算法直接读取2个文件并做相应输
出，中间就不需要先读完一个文件了）；
4.3 关于需求
    仔细阅读了需求文档，发现有好几处其实还不够清晰；第一个关于ui的，要求是“拥有类似如下界面”，那么
具体要求一模一样，还是类似就够了； 第二个是关于去重的，表格中为了清晰加入了空白行，结果现实的两个
文件中也还有空白行，这个不和需求了，要求去除两个文件相同的，都是空白行也该算相同所以去掉吧？ 第三个
还是关于去重的，到底与位置有没有关系呢？如果要尽力保留原始文件中内容的相对位置关系，那么要换一个算法
来实现，使用QList存储2个文件所有内容，以其中一个为标准遍历每一行，在另一个文件的QList中存在则要找出
所有的相同行，同时去掉，并且该被遍历的文件的QList中也要找出所有与之相同的行并一起删除，不然会漏删；
这也引出了第四个问题，就是同一个文件中相同的行是否存在？是否需要过滤，过滤的时候要不要考虑位置关系，
如果不允许倒可以留下一个那么该留下哪一个呢？如果不考虑位置关系那么就没必要用QList来存了，直接用QHash
会快很多；所以综上，本项目使用了QHash去重，允许同一个文件中的相同行（输出时相临近）；由此也可见需求
分析是非常的重要；实际项目中定会多多沟通每一个细节；此处暂时按以上说明和思路进行处理；

