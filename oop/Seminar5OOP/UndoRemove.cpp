//
// Created by razvan on 09.05.2019.
//

#include "UndoRemove.h"

void UndoRemove::executeUndo() {
    repository.addSong(deletedSong);
}

UndoRemove::UndoRemove(const Song &deletedSong, Repository &repository) : deletedSong(deletedSong),
                                                                          repository(repository) {}
