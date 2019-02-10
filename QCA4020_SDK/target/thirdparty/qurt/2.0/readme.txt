+ FreeRTOS contains the QuRT implementation for FreeRTOS.

+ Demo Make to compile QuRT Libraries.

+ These sources are compiled and tested with RVDS tool chain. 
  Customers can also rebuild using different tool chain 
  using demo make file.
  
+ QuRT libraries depends on safe implementation of string copy - 
   size_t strlcpy(char *dst, const char *src, size_t siz);
   Customers are expected to add implementation of strlcpy 
   for QuRT libraries to linkage.
   
+ QuRT libraries depends on FreeRTOS apis. Customers are
  expected to update demo file include path with FreeRTOS 
  include path.

+ Customer can access the QuRT library interface as part
  of Quartz SDK.
 
+ The current master branch is compatible with FreeRTOS_V8.2.1.

See also -
http://www.freertos.org/FreeRTOS-quick-start-guide.html
http://www.freertos.org/FAQHelp.html
