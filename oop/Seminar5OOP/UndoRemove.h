//
// Created by razvan on 09.05.2019.
//

#ifndef PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOREMOVE_H
#define PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOREMOVE_H


#include "Song.h"
#include "Repository.h"
#include "UndoAction.h"

class UndoRemove: public UndoAction {
private:
    Song deletedSong;
    Repository& repository;
public:
    void executeUndo() override;

    UndoRemove(const Song &deletedSong, Repository &repository);
};


#endif //PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOREMOVE_H
