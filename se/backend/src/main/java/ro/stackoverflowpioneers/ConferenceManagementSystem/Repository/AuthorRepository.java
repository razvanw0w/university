package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Author;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Room;

public interface AuthorRepository extends CrudRepository<Author,Integer> {
}
