# TscanCode
TscanCode 静态代码扫描工具

TscanCode旨在助力开发与测试人员从代码层面挖掘问题，将那些长期困扰项目的诸如空指针宕机等问题，扼杀于萌芽阶段。支持用户根据不同需求自定义配置检查项，有极强的扩展性和可维护性。平均扫描速度10W行/分钟.

TscanCode支持以下类型规则扫描：

应用特性

空指针检查，包含可疑的空指针，判空后解引用比如Crash等共3类subid检查

数据越界，Sprintf_S越界共1类subid检查

内存泄漏，分配和释放不匹配同1类subid检查

逻辑错误，重复的代码分支，bool类型和INT进行比较，表达式永远True或者false等共18类检查

可疑代码检查，if判断中含有可疑的=号，自由变量返回局部变量等共计15类检查

运算错误，判断无符号数小于0,对bool类型进行++自增等，共计11类检查
