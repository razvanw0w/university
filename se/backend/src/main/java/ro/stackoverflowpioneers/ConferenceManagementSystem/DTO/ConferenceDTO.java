package ro.stackoverflowpioneers.ConferenceManagementSystem.DTO;

public class ConferenceDTO {
    private int id;
    private String name;
    private String authorCode;
    private String listenerCode;

    public ConferenceDTO(int id, String name, String authorCode, String listenerCode) {
        this.id = id;
        this.name = name;
        this.authorCode = authorCode;
        this.listenerCode = listenerCode;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthorCode() {
        return authorCode;
    }

    public void setAuthorCode(String authorCode) {
        this.authorCode = authorCode;
    }

    public String getListenerCode() {
        return listenerCode;
    }

    public void setListenerCode(String listenerCode) {
        this.listenerCode = listenerCode;
    }
}
