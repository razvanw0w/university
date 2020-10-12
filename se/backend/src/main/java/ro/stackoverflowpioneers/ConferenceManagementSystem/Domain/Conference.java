package ro.stackoverflowpioneers.ConferenceManagementSystem.Domain;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Entity
public class Conference {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private String name;
    private Float fee;

    private Date startTime;
    private Date endTime;
    private Date abstractDeadline;
    private Date paperDeadline;

    private String chairCode;
    private String PCMemberCode;
    private String authorCode;
    private String listenerCode;

    @OneToMany
    private List<ProgramCommitteeMember> pcCommittee;

    @OneToMany
    private List<SteeringCommitteeMember> steeringCommittee;

    @OneToMany
    private List<ConferenceSection> sections = new ArrayList<>();

    @OneToMany
    private List<Proposal> proposals;

    @OneToMany
    private List<Proposal> acceptedProposals;

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

    public Float getFee() {
        return fee;
    }

    public void setFee(Float fee) { this.fee = fee; }

    public Date getStartTime() { return startTime; }

    public void setStartTime(Date startTime) { this.startTime = startTime; }

    public Date getEndTime() { return endTime; }

    public void setEndTime(Date endTime) { this.endTime = endTime; }

    public Date getAbstractDeadline() {
        return abstractDeadline;
    }

    public void setAbstractDeadline(Date abstractDeadline) {
        this.abstractDeadline = abstractDeadline;
    }

    public Date getPaperDeadline() { return paperDeadline; }

    public void setPaperDeadline(Date paperDeadline) { this.paperDeadline = paperDeadline; }

    //    public List<ProgramCommitteeMember> getPcCommittee() { return pcCommittee; }
//
//    public void setPcCommittee(List<ProgramCommitteeMember> pcCommittee) { this.pcCommittee = pcCommittee; }
//
//    public List<SteeringCommitteeMember> getSteeringCommittee() { return steeringCommittee; }
//
//    public void setSteeringCommittee(List<SteeringCommitteeMember> steeringCommittee) { this.steeringCommittee = steeringCommittee; }
//
    public List<ConferenceSection> getSections() {
        return sections;
    }

//    public void setSections(List<ConferenceSection> sections) { this.sections = sections; }
//
//    public List<Proposal> getProposals() { return proposals; }
//
//    public void setProposals(List<Proposal> proposals) { this.proposals = proposals; }
//
//    public List<Proposal> getAcceptedProposals() { return acceptedProposals; }
//
//    public void setAcceptedProposals(List<Proposal> acceptedProposals) { this.acceptedProposals = acceptedProposals; }
//
//    public void addProposal(Proposal prop){
//        proposals.add(prop);
//    }
//    public void addPCMember(ProgramCommitteeMember programCommitteeMember){
//        pcCommittee.add(programCommitteeMember);
//    }

    public void addSection(ConferenceSection section) {
        sections.add(section);
    }

    public void deleteSection(ConferenceSection section){
        sections.remove(section);
    }

    public String getChairCode() {
        return chairCode;
    }

    public void setChairCode(String chairCode) {
        this.chairCode = chairCode;
    }

    public String getPCMemberCode() {
        return PCMemberCode;
    }

    public void setPCMemberCode(String PCMemberCode) {
        this.PCMemberCode = PCMemberCode;
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
