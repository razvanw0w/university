//
// Created by razvan on 09.05.2019.
//

#ifndef PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOADD_H
#define PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOADD_H


#include "UndoAction.h"
#include "Song.h"
#include "Repository.h"

class UndoAdd: public UndoAction {
private:
    Song addedSong;
    Repository& repository;
public:
    void executeUndo() override;

    UndoAdd(const Song &addedSong, Repository &repository);
};


#endif //PLAYLIST___POLYMOPRHIC_UNDO___STUB_UNDOADD_H
