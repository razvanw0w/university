package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Entity
public class ConferenceSection {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private Integer noOfParticipants = 0;//apare de 2 ori pe diagrama
    private String name;

    private Date startTime;
    private Date endTime;

    @ManyToOne
    private Room room;

    @ManyToOne
    private ProgramCommitteeMember supervisor;
    @OneToMany
    @OnDelete(action = OnDeleteAction.CASCADE)
    @JoinColumn
    private List<Author> speakers = new ArrayList<>(); // string = author
    @OneToMany
    @OnDelete( action = OnDeleteAction.CASCADE)
    @JoinColumn
    private List<ConferenceUser> listeners = new ArrayList<>(); // string= conferenceParticipants

    public ConferenceSection() {
    }

    public ConferenceSection(String name, Date start, Date end) {
        this.name = name;
        this.startTime = start;
        this.endTime = end;
    }

    public Integer getId() {
        return id;
    }

    public Integer getNoOfParticipants() {
        return noOfParticipants;
    }

    public Integer getRoomNumber() {
        return room.getNumber();
    }

    public Date getStartTime() {
        return startTime;
    }

    public Date getEndTime() {
        return endTime;
    }

    public void setRoomNumber(Integer roomNumber) {
        room.setNumber(roomNumber);
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public void setListenersNull(){
        this.listeners = new ArrayList<ConferenceUser>();
    }
    public void setSpeakersNull(){
        this.speakers = new ArrayList<Author>();
    }

    public ProgramCommitteeMember getSupervisor() {
        return supervisor;
    }

    public void setNoOfParticipants(Integer noOfParticipants) {
        this.noOfParticipants = noOfParticipants;
    }

    public void setStartTime(Date startTime) {
        this.startTime = startTime;
    }

    public void setEndTime(Date endTime) {
        this.endTime = endTime;
    }

    public void setSupervisor(ProgramCommitteeMember supervisor) {
        this.supervisor = supervisor;
    }

    //    public void addListener(ConferencePaticipant listener){
//        listeners.add(listener);
//    }
//
    public void addSpeaker(Author speaker) {
        speakers.add(speaker);
    }

    public void addAuthor(Author author) {
        speakers.add(author);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Room getRoom() {
        return room;
    }

    public void setRoom(Room room) {
        this.room = room;
    }

    public List<Author> getSpeakers() {
        return speakers;
    }

    public List<ConferenceUser> getListeners() {
        return listeners;
    }

    public void addListener(ConferenceUser listener) {
        listeners.add(listener);
        ++noOfParticipants;
    }

    public void removeListener(ConferenceUser listener){
        listeners.remove(listener);
    }

    public void removeSpeakers(Author speaker){
        speakers.remove(speaker);
    }
}
