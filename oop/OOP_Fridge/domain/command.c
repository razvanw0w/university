//
// Created by razvan on 25.03.2019.
//

#include "command.h"

/**
 * This function creates a command based on two operations
 * @param redo: Operation* - the operation which must be done (redone)
 * @param undo: Operation* - the operation whici must be undone
 * @return: Command* - the newly created command
 */
Command* createCommand(Operation *redo, Operation* undo) {
    Command *command = (Command*)malloc(sizeof(Command));
    command->redo = redo;
    command->undo = undo;
    return command;
}

/**
 * This function destroys a command
 * @param command: Command* - the command which must be destroyed
 */
void destroyCommand(Command* command) {
    destroyOperation(command->redo);
    destroyOperation(command->undo);
    free(command);
}

Operation* getRedoOperation(Command* command) {
    return command->redo;
}

Operation* getUndoOperation(Command* command) {
    return command->undo;
}