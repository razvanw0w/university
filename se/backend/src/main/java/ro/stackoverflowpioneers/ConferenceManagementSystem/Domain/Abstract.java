package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Abstract {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Integer id;
    private String file;

    public Abstract() {
    }

    public Abstract(String file) {
        this.file = file;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getFile() {
        return file;
    }

    public void setFile(String file) {
        this.file = file;
    }
}
