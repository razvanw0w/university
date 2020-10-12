package ro.stackoverflowpioneers.ConferenceManagementSystem.Repository;

import org.springframework.data.repository.CrudRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ProgramCommitteeMember;

public interface PCMemberRepository extends CrudRepository<ProgramCommitteeMember,Integer> {
}
