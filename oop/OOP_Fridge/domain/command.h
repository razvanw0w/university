//
// Created by razvan on 25.03.2019.
//

#ifndef OOP3_COMMAND_H
#define OOP3_COMMAND_H

#include "operation.h"

typedef struct {
    Operation *redo;
    Operation *undo;
}Command;

Command* createCommand(Operation *redo, Operation* undo);
void destroyCommand(Command* command);
Operation* getRedoOperation(Command* command);
Operation* getUndoOperation(Command* command);

#endif //OOP3_COMMAND_H
