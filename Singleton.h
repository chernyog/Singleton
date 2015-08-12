
// 1. 解决.h文件
#define singletonInterface(className)           + (instancetype)shared##className;

// 2. 解决.m文件
// 判断 是否是 ARC
#if __has_feature(objc_arc)
#define singletonImplementation(className) \
static id instance; \
+ (instancetype)allocWithZone:(struct _NSZone *)zone { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        instance = [super allocWithZone:zone]; \
    }); \
    return instance; \
} \
+ (instancetype)shared##className { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        instance = [[self alloc] init]; \
    }); \
    return instance; \
} \
- (id)copyWithZone:(NSZone *)zone { \
    return instance; \
}
#else 
// MRC 部分
#define singletonImplementation(className) \
static id instance; \
+ (instancetype)allocWithZone:(struct _NSZone *)zone { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        instance = [super allocWithZone:zone]; \
    }); \
    return instance; \
} \
+ (instancetype)shared##className { \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        instance = [[self alloc] init]; \
    }); \
    return instance; \
} \
- (id)copyWithZone:(NSZone *)zone { \
    return instance; \
} \
- (oneway void)release {} \
- (instancetype)retain {return instance;} \
- (instancetype)autorelease {return instance;} \
- (NSUInteger)retainCount {return ULONG_MAX;}

#endif

// 提示，最后一行不要使用 \