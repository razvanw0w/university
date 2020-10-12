package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import com.fasterxml.jackson.annotation.JsonManagedReference;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

@Entity
@Inheritance(strategy = InheritanceType.JOINED)
public class ProgramCommitteeMember extends ConferenceUser {

    @ManyToMany(fetch = FetchType.EAGER,
        cascade = {CascadeType.PERSIST, CascadeType.MERGE},
    mappedBy = "reviewers")
    @JsonManagedReference
    private Set<Proposal> reviewProposals = new HashSet<>();

    @ManyToMany(fetch = FetchType.EAGER,
            cascade = {CascadeType.PERSIST, CascadeType.MERGE},
            mappedBy = "refusedReview")
    @JsonManagedReference
    private Set<Proposal> refusedProposals = new HashSet<>();

    public ProgramCommitteeMember() {
    }

    protected Integer conferenceId;

    public ProgramCommitteeMember(Integer conferenceId, String name, String affiliation, String email, String webpage, String username, String password) {
        super(name, affiliation, email, webpage, username, password);
        this.conferenceId = conferenceId;
    }

    public Integer getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(Integer conferenceId) {
        this.conferenceId = conferenceId;
    }

    public Set<Proposal> getReviewProposals() {
        return reviewProposals;
    }

    public void setReviewProposals(Set<Proposal> reviewProposals) {
        this.reviewProposals = reviewProposals;
    }

    public Set<Proposal> getRefusedProposals() {
        return refusedProposals;
    }

    public void setRefusedProposals(Set<Proposal> refusedProposals) {
        this.refusedProposals = refusedProposals;
    }

    //    public void acceptProposalforReview(Conference conference,Proposal proposal){};
//    public void refuseProposalforReview(Conference conference,Proposal proposal){};
//    public void reviewPaper(Conference conference,Proposal proposal,Integer rating){};
}
