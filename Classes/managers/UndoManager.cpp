#include "managers/UndoManager.h"

namespace cardgame {

UndoManager::UndoManager(UndoModel* model)
    : _undoModel(model)
{
}

void UndoManager::pushRecord(const UndoRecord& record)
{
    if (_undoModel)
    {
        _undoModel->records.push_back(record);
    }
}

bool UndoManager::canUndo() const
{
    return _undoModel && !_undoModel->records.empty();
}

bool UndoManager::popRecord(UndoRecord& outRecord)
{
    if (!canUndo())
    {
        return false;
    }

    outRecord = _undoModel->records.back();
    _undoModel->records.pop_back();
    return true;
}

} // namespace cardgame
