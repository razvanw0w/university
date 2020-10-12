package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.Entity;

@Entity
public class SteeringCommitteeMember extends ConferenceUser { //extends user
    private Integer conferenceId = -1;

    public SteeringCommitteeMember() {
    }

    public SteeringCommitteeMember(String name, String affiliation, String email, String webpage, String username, String password) {
        super(name, affiliation, email, webpage, username, password);
    }

    public Integer getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(Integer conferenceId) {
        this.conferenceId = conferenceId;
    }

    //    public Conference createConference(String name, Date startTime, Date endTime){
//        Conference conference = new Conference(name, startTime, endTime);
//    }

//    public void invitePCMember(Conference conference, String username) {
//    }

}
