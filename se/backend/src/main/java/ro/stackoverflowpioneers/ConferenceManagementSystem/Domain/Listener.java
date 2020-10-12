package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;


import javax.persistence.Entity;

@Entity
public class Listener extends ConferenceUser {
    public Listener() {
    }

    private Integer conferenceId;

    public Listener(Integer conferenceId, String name, String affiliation, String email, String webpage, String username, String password) {
        super(name, affiliation, email, webpage, username, password);
        this.conferenceId = conferenceId;
    }

    public Integer getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(Integer conferenceId) {
        this.conferenceId = conferenceId;
    }
}
