# Byte-BinaryString-Interconversion

Brief description:Convert byte stream  to binary string or oppositely binary string be converted to byte stream！

标题：C++字节流与二进制字符串相互转换（一个简单的明文加解密程序）

**1.想法由来**

作为一名程序猿，在我们写文章、文字片段或者一句简短的话语，对外发表或者告之他人时，是否想过带点新意和创意呢？如果想过，那么这篇文章会给你一点帮助。 本文介绍的是一个简单的将明文与二进制字符串相互转换的工具，尚未提供私有秘钥加密的功能，后续如有需要或网友有兴趣可自行扩展其功能。之所以写这个小工具，是因为我在写一篇blog时，一些较为私密的信息不想那么明显的公之于众，简单的将其转换成对应的二进制字符串，这样一来，既增加了对方对加密后文字的兴趣，也避免了敏感信息直白表述带来的尴尬，又体现自己的程序猿特质，难道不是一个一举多得的idea么。

**2.应用场景**

有了这个小工具，把我们的明文转换成对应的二进制字符串，其主要应用场景有： 
（1）屌丝程序猿向女神表白。 将自己的心意大胆的说出来吧，别怕别人笑话，因为不懂01的他们根本不知道你写的是什么。也别怕女神看不明白，懂你在乎你的人，她会去向你再三询问的，如果你的女神也是个程序媛，那就简单多了！使用01表白，是不是很有feel呢？ 
（2）加密自己私密的信息。 比如自己做了一些不该做的事，犯了一些不该犯的错，想了一个不该想的人，内心独白，情感宣泄等等，不想被岁月渐渐的抹去，淡忘在时间的银河里，那就勇敢的记录下来吧！用这个小工具加个密，不怕别人看的到，就怕他看不懂！ 

**3.编译**

因为只有一个源文件，编译很简单。
```
g++ byte2binarystring.cpp -o b2bs.out
```
姑且给这个程序命名为b2bs。如果是多个源文件编译的话，那么在Linux下可就要写makefile了。下面给出自己总结的一个很好用的makefile模板，别人一般我不告诉他！ 
```
################################### 
#@brief:make scripts template 
#@author:dablelv 
################################## 
#environment 
var VPATH+=dir1:dir2 
CC:=g++ FLAGS=-g -Wall -std=c++11 
INC+=-IheadDir1 -IheadDir2 
LIBDIR+=-LlibDir1 -LlibDir2 
CPPDIRS=srcdir1 srcdir2 
TARGET:=yourTarget 
CPPS=$(shell for dir in ${CPPDIRS};do echo $${dir}/*.cpp;done) OBJDIR=objDir 
OBJS=$(patsubst %.cpp,${OBJDIR}/%.o,$(notdir ${CPPS})) 
${TARGET}:
${OBJS} ${CC} ${FLAGS} ${OBJS} -o $@ ${LIBDIR} 
${OBJDIR}/%.o:%.cpp 
${CC} ${FLAGS} ${INC} -o $@ -c $<
.PHONY:clean clean: rm -f ${TARGET} ${OBJDIR}/*
```

**4.使用说明与示例**

代码中已经有详细的注释了，我再贴一下，也可使用命令`b2bs.out -h`来查看使用说明。
```
Usage: 
encryption:b2bs.out -e -O -f [inputFile] -o [outFile] 
decryption:b2bs.out -d -O -f [inputFile] -o [outFile] 
Options: 
-e <encrypt> encrypt chinese to binary string. 
-d <decrypt> decrypt binary string to chinese. 
-f <file> specify the input file. 
-o <output> specify the output file. 
-O <Output> output the descrypt or encrypt result to standard output. 
-h or --help output help information. 
```

**使用示例：**
将"里约奥运，中国加油！"写在文本文档，以任意编码存放，我这里使用notepad++编辑以utf-8无BOM来存放。BOM（Byte Order Mark）指的是字节序，出现在文本文件头部，用来指明一个由多个字节表示的非ASCII字符的字节顺序。Windows还使用BOM来标记文本文件的编码方式，Linux一般不需要BOM。 

将明文文本（字节流）转为二进制字符串：
```
b2bs.out -e -f inputFile -o outFile
```
打开outFile，我们会看到如下二进制字符串：
```
111010011000011110001100111001111011101010100110111001011010010110100101111010001011111110010000111011111011110010001100111001001011100010101101111001011001101110111101111001011000101010100000111001101011001010111001111011111011110010000001
```
将上面二进制字符串转成明文文本（字节流）：
```
shell b2bs.out -d -f outFile -o newOutFile
```
打开newOutFile你将会看到解密后的明文：
里约奥运，加油中国！

**5.小结**

最近因在腾讯实习的工作不是很紧张，忙里偷闲写了这个小工具，感觉还是挺好玩的，有心人可以给它做一个GUI，穿上一套衣服，感觉裸奔不太友好，或者增加秘钥加密的功能等等！最近这两天也迎来实习转正考核，希望一切顺利，也祝愿一同实习的小伙伴们考核顺利，校招圆满，有个满意的归宿！ 
