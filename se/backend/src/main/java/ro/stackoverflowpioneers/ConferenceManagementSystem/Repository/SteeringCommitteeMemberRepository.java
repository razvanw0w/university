package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.SteeringCommitteeMember;

public interface SteeringCommitteeMemberRepository extends CrudRepository<SteeringCommitteeMember, Integer> {
}
