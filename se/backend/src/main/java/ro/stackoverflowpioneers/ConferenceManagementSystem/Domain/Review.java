package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

//si facem 4 de astea pentru fiecare
@Entity
public class Review {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;


    private Integer proposalId;
    private int reviewQualifierGrade;

    public Review() {
    }

    public Review(int proposalId, int reviewQualifierGrade) {
        this.proposalId = proposalId;
        this.reviewQualifierGrade = reviewQualifierGrade;
    }
}
