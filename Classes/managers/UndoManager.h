#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "models/UndoModel.h"

/**
 * @brief Manages the undo stack and access patterns.
 * @details Provides push/pop operations on UndoModel.
 */
namespace cardgame {

class UndoManager
{
public:
    /**
     * @brief Construct with an external undo model.
     * @param model Undo model pointer (not owned).
     */
    explicit UndoManager(UndoModel* model);

    /**
     * @brief Push an undo record.
     * @param record Undo record to push.
     */
    void pushRecord(const UndoRecord& record);

    /**
     * @brief Check if undo is available.
     * @return true if there is at least one record.
     */
    bool canUndo() const;

    /**
     * @brief Pop the last undo record.
     * @param outRecord Output record.
     * @return true when a record is returned.
     */
    bool popRecord(UndoRecord& outRecord);

private:
    /** @brief Undo model pointer (not owned). */
    UndoModel* _undoModel = nullptr;
};

} // namespace cardgame

#endif // UNDO_MANAGER_H
