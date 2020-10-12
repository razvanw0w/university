package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Room;

public interface RoomRepository extends CrudRepository<Room,Integer> {

}
