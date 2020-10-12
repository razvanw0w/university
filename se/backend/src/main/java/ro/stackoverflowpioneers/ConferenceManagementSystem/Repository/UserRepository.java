package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ConferenceUser;

public interface UserRepository extends CrudRepository<ConferenceUser, Integer> {

}
