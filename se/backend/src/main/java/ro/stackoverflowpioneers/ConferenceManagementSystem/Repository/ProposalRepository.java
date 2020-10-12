package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Proposal;

public interface ProposalRepository extends CrudRepository<Proposal, Integer> {
}
