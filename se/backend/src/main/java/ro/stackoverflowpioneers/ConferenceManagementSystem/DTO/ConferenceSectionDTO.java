package ro.stackoverflowpioneers.ConferenceManagementSystem.DTO;

public class ConferenceSectionDTO {
    private int sectionId;
    private String conferenceName;
    private String sectionName;
    private int roomNumber;
    private int noOfParticipants;

    public ConferenceSectionDTO() {
    }

    public ConferenceSectionDTO(int sectionId, String conferenceName, String sectionName, int roomNumber, int noOfParticipants) {
        this.sectionId = sectionId;
        this.conferenceName = conferenceName;
        this.sectionName = sectionName;
        this.roomNumber = roomNumber;
        this.noOfParticipants = noOfParticipants;
    }

    public int getSectionId() {
        return sectionId;
    }

    public void setSectionId(int sectionId) {
        this.sectionId = sectionId;
    }

    public String getConferenceName() {
        return conferenceName;
    }

    public void setConferenceName(String conferenceName) {
        this.conferenceName = conferenceName;
    }

    public String getSectionName() {
        return sectionName;
    }

    public void setSectionName(String sectionName) {
        this.sectionName = sectionName;
    }

    public int getRoomNumber() {
        return roomNumber;
    }

    public void setRoomNumber(int roomNumber) {
        this.roomNumber = roomNumber;
    }

    public int getNoOfParticipants() {
        return noOfParticipants;
    }

    public void setNoOfParticipants(int noOfParticipants) {
        this.noOfParticipants = noOfParticipants;
    }
}
