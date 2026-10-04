# il2cpp_plus

原始il2cpp是AOT运行时，不支持动态注册dll元数据。我们轻微改造了metadata管理模块，插入了一些hook代码，支持动态加载dll元数据。

注意，此项目代码不能单独工作，甚至无法成功编译。必须配合 [HybridCLR](https://github.com/focus-creative-games/hybridclr) 解释器才能正常工作。

main分支不包含任何代码，请切到正确的版本。

Unity 2022 opt8 使用上游 `v2022-8.11.0` 基线，配套 HybridCLR
`v8.13.0-opt8` 和 DHE `dhe-runtime-v35`。本轮 `libil2cpp` 接入代码与 opt7
相同，性能与缓存改动位于 HybridCLR 仓库。运行时更新需要重新构建 Base。
当前验证范围为 Unity 2022.3.62f3 Windows；ARM64 真机和完整性能验收仍待完成。
