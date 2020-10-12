package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;


import javax.persistence.*;

@Entity
public class Paper {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private String title;
    private String paperFile;

    @OneToOne
    private Abstract paperAbstract;

}
