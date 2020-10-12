package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.Entity;

@Entity
public class Author extends ConferenceUser {
//    @OneToMany
//    private List<Proposal> proposals;

    Integer conferenceId;

    public Author() {
    }

    public Author(Integer conferenceId, String name, String affiliation, String email, String webpage, String username, String password) {
        super(name, affiliation, email, webpage, username, password);
        this.conferenceId = conferenceId;
    }

    public Integer getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(Integer conferenceId) {
        this.conferenceId = conferenceId;
    }

    public void submitProposal(String conference, String proposal) {
        //todo implement method
    }

    public void uploadPaper(String proposal, String paper) {
        //todo implement method
    }

    public void uploadAbstract(String conference, String proposal) {
        //todo implement method
    }

    public void uploadPresentation(String conference, String proposal) {
        //todo implement method
    }
}
