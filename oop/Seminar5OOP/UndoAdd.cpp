//
// Created by razvan on 09.05.2019.
//

#include "UndoAdd.h"

void UndoAdd::executeUndo() {
    repository.removeSong(addedSong);
}

UndoAdd::UndoAdd(const Song &addedSong, Repository &repository) : addedSong(addedSong), repository(repository) {}
