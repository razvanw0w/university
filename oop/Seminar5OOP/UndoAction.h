//
// Created by razvan on 09.05.2019.
//

#ifndef PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOACTION_H
#define PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOACTION_H


class UndoAction {
public:
    virtual ~UndoAction();
    virtual void executeUndo() = 0;
};


#endif //PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOACTION_H
