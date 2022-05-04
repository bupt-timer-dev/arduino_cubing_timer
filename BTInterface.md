# 蓝牙BLE接口

__*注：以下内容中服务器指计时器硬件__


## 特征(Characteristic)：

TIMING(UUID:8F3984DE-E8F8-47CB-919C-C9EC3DC2F0DB):

该特征为notify/read/write特征，类型为int，标识服务器是否在计时中。

当服务器计时状态变化时发送notify
当该特征被写入时，服务器会相应更改自身的计时状态

TIME(UUID:8F3984DF-E8F8-47CB-919C-C9EC3DC2F0DB):

该特征为read特征，类型为uint32_t，标识本次计时时长，单位为ms。