package ro.stackoverflowpioneers.ConferenceManagementSystem.DTO;

public class UserLoginDTO {
    private Integer userId;
    private Integer conferenceId;

    public UserLoginDTO() {
    }

    public UserLoginDTO(Integer userId, Integer conferenceId) {
        this.userId = userId;
        this.conferenceId = conferenceId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public Integer getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(Integer conferenceId) {
        this.conferenceId = conferenceId;
    }

    @Override
    public String toString() {
        return "UserLoginDTO{" +
                "userId=" + userId +
                ", conferenceId=" + conferenceId +
                '}';
    }
}
