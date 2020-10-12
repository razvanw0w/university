package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import com.fasterxml.jackson.annotation.JsonBackReference;

import javax.persistence.*;
import java.io.File;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

@Entity
public class Proposal {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    private String authors;
    private String keywords;
    private String topics;
    private String abstractFile;
    private String title;
    private String paperFile;
    private String status;
    private Integer idAuthor;
    private String reviews = "";

    public byte[] getAbstFile() {
        return abstFile;
    }

    public void setAbstFile(byte[] abstFile) {
        this.abstFile = abstFile;
    }

    private byte[] abstFile;

    public byte[] getPapFile() {
        return papFile;
    }

    public void setPapFile(byte[] papFile) {
        this.papFile = papFile;
    }

    private byte[] papFile;


    @ManyToMany(fetch = FetchType.EAGER, cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    @JoinTable(name = "proposals_reviewers",
        joinColumns = {@JoinColumn(name = "proposal_id")},
        inverseJoinColumns = {@JoinColumn(name = "reviewer_id")})
    @JsonBackReference
    private Set<ProgramCommitteeMember> reviewers = new HashSet<>();

    @ManyToMany(fetch = FetchType.EAGER, cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    @JoinTable(name = "proposals_refusers",
            joinColumns = {@JoinColumn(name = "proposal_id")},
            inverseJoinColumns = {@JoinColumn(name = "reviewer_id")})
    @JsonBackReference
    private Set<ProgramCommitteeMember> refusedReview = new HashSet<>();

    public String getReviews() {
        return reviews;
    }

    public void setReviews(String reviews) {
        this.reviews = reviews;
    }

    public Proposal() {
    }

    public Proposal(String authors, String keywords, String topics, String paper, String abstractFile, String title, String paperFile,Integer idAuthor) {
        this.authors = authors;
        this.keywords = keywords;
        this.topics = topics;
        this.abstractFile = abstractFile;
        this.title = title;
        this.paperFile = paperFile;
        this.idAuthor = idAuthor;
//        this.status = "Not yet reviewed";
    }


    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getAuthors() {
        return authors;
    }

    public void setAuthors(String authors) {
        this.authors = authors;
    }

    public String getKeywords() {
        return keywords;
    }

    public void setKeywords(String keywords) {
        this.keywords = keywords;
    }

    public String getTopics() {
        return topics;
    }

    public void setTopics(String topics) {
        this.topics = topics;
    }

    public Set<ProgramCommitteeMember> getReviewers(){return this.reviewers;}

    public void setReviewers( ProgramCommitteeMember pcm)
    {
        this.reviewers.add(pcm);
    }

    public String getAbstractFile() {
        return abstractFile;
    }

    public void setAbstractFile(String abstractFile) {
        this.abstractFile = abstractFile;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getPaperFile() {
        return paperFile;
    }

    public void setPaperFile(String paperFile) {
        this.paperFile = paperFile;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setReviewers(Set<ProgramCommitteeMember> reviewers) {
        this.reviewers = reviewers;
    }

    public Set<ProgramCommitteeMember> getRefusedReview() {
        return refusedReview;
    }

    public void setRefusedReview(Set<ProgramCommitteeMember> refusedReview) {
        this.refusedReview = refusedReview;
    }

    public void addReview(String review) {
        if (this.reviews.equals("")) {
            this.reviews = review;
        } else {
            this.reviews += "," + review;
        }
        System.out.println(this.reviews);
        updateStatus();
    }

    public boolean isAccepted() {
        return status.equals("Accepted");
    }

    public Integer getIdAuthor() {
        return idAuthor;
    }

    public void setIdAuthor(Integer id) {
        this.idAuthor = id;
    }

    private void updateStatus() {
        boolean outcome = Arrays.stream(reviews.split(","))
                .map(Integer::parseInt)
                .filter(grade -> grade >= 4).count() >= reviews.split(",").length / 2;
        if (outcome) {
            status = "Accepted";
        } else {
            status = "Refused";
        }
    }
}
