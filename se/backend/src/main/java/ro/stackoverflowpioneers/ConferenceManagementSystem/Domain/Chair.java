package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.Entity;

@Entity
public class Chair extends ConferenceUser {
    public Chair() {
    }

    protected Integer conferenceId;

    public Chair(Integer conferenceId, String name, String affiliation, String email, String webpage, String username, String password) {
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
