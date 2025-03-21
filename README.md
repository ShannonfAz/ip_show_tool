# ip_show_tool
# WARNING:仅基于逐飞方案，使用逐飞内核，使用逐飞扩展板或屏幕引脚与逐飞扩展板相同，且板子上有p13-p16按键可用该工具
- 一个可用于开机显示板子ip的程序及源码，基于逐飞开源库开发，专治莫名其妙变ip
- 用法：去release把那个ip_show下载下来，丢到99派的/home/root，然后chmod 777 ip_show，然后配开机自启就是
- 开机自启配法：
- 开板子，连ssh
- vi /etc/rc.local
- 先找别人的教程配wifi，如果你是wifi版99派（强力推荐，远程丢代码主打一个方便，也就贵10r）
- 如果你已配好wifi，那就往udhcpc -i wlan0 &下面加上如下内容：
- sleep 3
- /home/root/ip_show &
- （假使你把ip_show放到了/home/root）（括号内这些说明就别写上去了）（到这里就结束了）
- 
- 发癫：2k3000什么时候能出来啊，急急急急急.gif
- 附：什么叫基于逐飞开源库开发，分明是我把deepseek生成的代码魔改一通编译一下丢到这里来了，感谢deepseek开源.jpg
