package ro.stackoverflowpioneers.ConferenceManagementSystem.DTO;

public class ProposalDTO {
    private Integer id;
    private String title;
    private String authors;
    private String paperFile;
    private String abstractFile;
    private String status;


    public ProposalDTO(Integer id, String title, String authors, String paperFile, String abstractFile, String status) {
        this.id = id;
        this.title = title;
        this.authors = authors;
        this.paperFile = paperFile;
        this.abstractFile = abstractFile;
        this.status = status;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthors() {
        return authors;
    }

    public void setAuthors(String authors) {
        this.authors = authors;
    }

    public String getPaperFile() {
        return paperFile;
    }

    public void setPaperFile(String paperFile) {
        this.paperFile = paperFile;
    }

    public String getAbstractFile() {
        return abstractFile;
    }

    public void setAbstractFile(String abstractFile) {
        this.abstractFile = abstractFile;
    }
}
