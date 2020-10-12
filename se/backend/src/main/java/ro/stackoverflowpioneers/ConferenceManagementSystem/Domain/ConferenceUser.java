package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.*;
import java.util.List;

@Entity
@Inheritance(strategy = InheritanceType.JOINED)
public class ConferenceUser {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    protected Integer id;

    protected String name;
    protected String affiliation;
    protected String email;
    protected String webpage;
    protected String username;
    protected String password;
    @OneToMany
    protected List<Conference> paidConferences;

    protected ConferenceUser() {
    }

    public ConferenceUser(String name, String affiliation, String email, String webpage, String username, String password) {
        this.name = name;
        this.affiliation = affiliation;
        this.email = email;
        this.webpage = webpage;
        this.username = username;
        this.password = password;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAffiliation() {
        return affiliation;
    }

    public void setAffiliation(String affilitaion) {
        this.affiliation = affilitaion;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getWebpage() {
        return webpage;
    }

    public void setWebpage(String webpage) {
        this.webpage = webpage;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
