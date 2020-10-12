package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ConferenceSection;

public interface ConferenceSectionRepository extends CrudRepository<ConferenceSection,Integer> {
}
