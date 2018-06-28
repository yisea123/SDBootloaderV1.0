
set "Ymd=%date:~,4%%date:~5,2%%date:~8,2%"
set "pwd=D:\Keil5Projects\STM32Projects"
set "backuppwd=%pwd%\backup"
md %backuppwd%
"%ProgramFiles%\WinRAR"\rar a -pfeng2008 %backuppwd%\SDBootloaderV1.0%Ymd%.rar "%pwd%\SDBootloaderV1.0"

dir %backuppwd%

pause