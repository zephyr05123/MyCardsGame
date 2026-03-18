# 程序设计说明 

## 模块边界 
- configs：静态配置模型和加载器（level JSON, card resources）。 
- models：运行时游戏数据（卡牌、区域、撤销堆栈）。模型提供 JSON 序列化。 
- views：仅用于布局和动画的 UI 节点。视图仅公开回调和视觉状态。 
- controllers：在模型和视图之间协调用户输入和业务逻辑。 
- manages：由控制器拥有的有状态辅助工具（撤销管理器）。 
- services：无状态逻辑（匹配规则、模型生成）。 
- utils：公共的enums和小工具。 

## 添加新卡牌资源 
1. 将新资源放置在 `res/number` 或 `res/suits` 中（或在 `res` 下添加新目录）。
2. 更新 `Classes/configs/models/CardResConfig.cpp`：如果添加了新的花色/牌面资源，请扩展 `getSuitIconFile` 或 `getBigNumberFile` 映射。
3. 如果引入了新的花色/牌面资源，请在 `Classes/utils/CardTypes.h` 中扩展枚举，并更新 `CardMatchService` 中的任何匹配逻辑。

## 添加新的撤销类型 
1. 在 `Classes/models/UndoModel.h` 中扩展 `UndoRecord` 以添加新的记录形状。
2. 在 `GameController::handleUndo()` 中添加一个新的处理程序，用于识别新记录并恢复模型和视图状态。
3. 当执行新操作时，通过 `UndoManager::pushRecord` 推送新的记录类型。
4. 如有需要，在 `GameView` 中添加辅助方法以实现视觉回滚（例如，将卡牌移回自定义区域）。