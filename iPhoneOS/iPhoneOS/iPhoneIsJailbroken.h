
#import <Foundation/Foundation.h>
#import <sys/stat.h>
#import <UIKit/UIKit.h>
#include <mach-o/dyld.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dlfcn.h>
#include "TargetConditionals.h"


NS_ASSUME_NONNULL_BEGIN

@interface iPhoneIsJailbroken : NSObject

BOOL isJb(void);
BOOL isInjectedWithDynamicLibrary(void);
BOOL isSecurityCheckPassed(void);
BOOL isDebugged(void);
BOOL isFromAppStore(void);

@end

NS_ASSUME_NONNULL_END
