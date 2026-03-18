#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "models/UndoModel.h"

/**
 * @brief Manages undo stack for playfield matches.
 */
namespace cardgame {

class UndoManager
{
public:
    explicit UndoManager(UndoModel* model);

    void pushRecord(const UndoRecord& record);
    bool canUndo() const;
    bool popRecord(UndoRecord& outRecord);

private:
    UndoModel* _undoModel = nullptr;
};

} // namespace cardgame

#endif // UNDO_MANAGER_H
