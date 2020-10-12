package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.ConferenceDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.ConferenceSectionDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.*;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Controller
@RequestMapping("/conferences")
@CrossOrigin(origins = "*", allowedHeaders = "*")
public class ConferenceController {
    @Autowired
    private ConferenceRepository conferenceRepository;

    @Autowired
    private ListenerRepository listenerRepository;

    @Autowired
    private SteeringCommitteeMemberRepository steeringCommitteeMemberRepository;

    @Autowired
    private PCMemberRepository pcMemberRepository;

    @Autowired
    private ProposalRepository proposalRepository;

    @Autowired
    private ConferenceSectionRepository conferenceSectionRepository;

    @Autowired
    private AuthorRepository authorRepository;

    @Autowired
    private RoomRepository roomRepository;

    @Autowired
    private UserRepository userRepository;

    @PostMapping(path = "/add")
    @CrossOrigin(origins = "http://localhost:3000")
    public @ResponseBody
    String addNewConference(@RequestParam Integer userId,
                            @RequestParam String name, @RequestParam Float fee,
                            @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date abstractDeadline,
                            @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date paperDeadline,
                            @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date startTime,
                            @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date endTime,
                            @RequestParam String chairCode,
                            @RequestParam String PCMemberCode,
                            @RequestParam String authorCode,
                            @RequestParam String listenerCode) {
        Conference conf = new Conference();
        conf.setName(name);
        conf.setFee(fee);
        conf.setAbstractDeadline(abstractDeadline);
        conf.setPaperDeadline(paperDeadline);
        conf.setStartTime(startTime);
        conf.setEndTime(endTime);
        conf.setChairCode(chairCode);
        conf.setPCMemberCode(PCMemberCode);
        conf.setAuthorCode(authorCode);
        conf.setListenerCode(listenerCode);

//        // ONLY FOR TESTING PURPOSES -- START
//        ConferenceSection section1 = new ConferenceSection();
//        section1.setId(2);
//        ConferenceSection section2 = new ConferenceSection();
//        section2.setId(3);
//
//        conf.addSection(section1);
//        conf.addSection(section2);
//        // ONLY FOR TESTING PURPOSES -- END
        conferenceRepository.save(conf);
        SteeringCommitteeMember steeringCommitteeMember = steeringCommitteeMemberRepository.findById(userId).orElseThrow(RuntimeException::new);
        steeringCommitteeMember.setConferenceId(conf.getId());
        steeringCommitteeMemberRepository.save(steeringCommitteeMember);
        return conf.getId().toString();
    }

    @PostMapping(path = "/delete")
    public @ResponseBody
    String deleteConference(@RequestParam int id)
    {
        Optional<Conference> opt = conferenceRepository.findById(id);
        if(!opt.isPresent())
            return "That id doesn't exist!";
        conferenceRepository.deleteById(id);
        return "Deleted";
    }

    @GetMapping(path = "/all")
    public @ResponseBody
    Iterable<ConferenceDTO> getAllConference() {
        return StreamSupport.stream(conferenceRepository.findAll().spliterator(), false)
                .map(conference -> new ConferenceDTO(conference.getId(), conference.getName(), conference.getAuthorCode(), conference.getListenerCode()))
                .collect(Collectors.toList());
    }


    @PostMapping(path = "/changeAbstractDeadline")
    public @ResponseBody String changeAbstractDeadline(@RequestParam int id, @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date deadline){
        Conference conf = new Conference();
        conferenceRepository.findById(id).ifPresent(conference -> {
            conf.setPaperDeadline(conference.getPaperDeadline());
            conf.setFee(conference.getFee());
            conf.setName(conference.getName());
            conf.setEndTime(conference.getEndTime());
            conf.setStartTime(conference.getStartTime());
        });
        conf.setAbstractDeadline(deadline);
        conf.setId(id);
        conferenceRepository.save(conf);
        return "Abstract deadline changed";
    }

    @PostMapping(path = "/changePaperDeadline")
    public @ResponseBody String changePaperDeadline(@RequestParam int id, @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date deadline){
        Conference conf = new Conference();
        conferenceRepository.findById(id).ifPresent(conference -> {
            conf.setAbstractDeadline(conference.getAbstractDeadline());
            conf.setFee(conference.getFee());
            conf.setName(conference.getName());
            conf.setEndTime(conference.getEndTime());
            conf.setStartTime(conference.getStartTime());
        });
        conf.setPaperDeadline(deadline);
        conf.setId(id);
        conferenceRepository.save(conf);
        return "Paper deadline changed";
    }

    @GetMapping(path = "/{id}/planning")
    public @ResponseBody
    Iterable<ConferenceSectionDTO> getThirdPhasePlanning(@PathVariable int id) {
        Optional<Conference> conferenceOptional = conferenceRepository.findById(id);
        Conference conference = conferenceOptional.orElseThrow(() -> new RuntimeException("planning request for non-existing conference"));
        List<ConferenceSectionDTO> conferenceSectionDTOList = conference.getSections().stream()
                .map(section -> new ConferenceSectionDTO(section.getId(), conference.getName(), section.getName(), section.getRoomNumber(), section.getNoOfParticipants()))
                .collect(Collectors.toUnmodifiableList());
        return conferenceSectionDTOList;
    }

    @GetMapping(path= "/code")
    public @ResponseBody
    Iterable<String> getCode(@RequestParam String cod) {
        List<Conference> confs = (List<Conference>) conferenceRepository.findAll();
        List<String> result = new ArrayList<>();
        confs.forEach(c -> {
            if (c.getAuthorCode().equals(cod)) {
                result.add("author");
                result.add(c.getId().toString());
            }
            if (c.getChairCode().equals(cod)) {
                result.add("chair");
                result.add(c.getId().toString());
            }
            if (c.getListenerCode().equals(cod)) {
                result.add("listener");
                result.add(c.getId().toString());
            }
            if (c.getPCMemberCode().equals(cod)) {
                result.add("pcmember");
                result.add(c.getId().toString());
            }
        });
        return result;
    }

    @GetMapping(path = "/generateSections")
    @Transactional
    public @ResponseBody
    String generateSections(@RequestParam Integer conferenceId) {
        Conference conference = conferenceRepository.findById(conferenceId).orElseThrow(RuntimeException::new);

        List<ConferenceSection> conferenceSection  = (List<ConferenceSection>) conferenceSectionRepository.findAll();
        conferenceSection.forEach(section -> {
            conference.deleteSection(section);
            section.setListenersNull();
            section.setSpeakersNull();
            conferenceSectionRepository.deleteById(section.getId());
        });

        //Conference conference = conferenceRepository.findById(conferenceId).orElseThrow(RuntimeException::new);
        List<Proposal> acceptedPapers = getAcceptedPapers();

        Map<String, List<Proposal>> topicsPapers = acceptedPapers.stream()
                .collect(Collectors.groupingBy(Proposal::getTopics));
        List<ConferenceSection> conferenceSections = topicsPapers.keySet().stream()
                .map(topic -> new ConferenceSection(topic, new Date(), new Date()))
                .collect(Collectors.toList());

        Random rand = new Random();
        List<ProgramCommitteeMember> programCommitteeMembers = StreamSupport.stream(pcMemberRepository.findAll().spliterator(), false).collect(Collectors.toList());
        List<Room> rooms = StreamSupport.stream(roomRepository.findAll().spliterator(), false).collect(Collectors.toList());
        for (ConferenceSection section : conferenceSections) {
            String topicName = section.getName();
            List<Proposal> proposals = topicsPapers.get(topicName);
            proposals.forEach(proposal -> section.addAuthor(authorRepository.findById(proposal.getIdAuthor()).orElseThrow(RuntimeException::new)));
            section.setSupervisor(programCommitteeMembers.get(rand.nextInt(programCommitteeMembers.size())));
            section.setRoom(rooms.get(rand.nextInt(rooms.size())));
            conferenceSectionRepository.save(section);
            conference.addSection(section);
        }
        conferenceRepository.save(conference);
        return "Generated";
    }

    @PostMapping(path = "/addListenerToSection")
    public @ResponseBody
    String addListenerToSection(@RequestParam Integer conferenceId, @RequestParam Integer sectionId, @RequestParam Integer userId) {
        Conference conference = conferenceRepository.findById(conferenceId).orElseThrow(RuntimeException::new);
        ConferenceSection conferenceSection = conference.getSections().stream().filter(section -> section.getId().equals(sectionId)).findFirst().orElseThrow(RuntimeException::new);
        ConferenceUser conferenceUser = userRepository.findById(userId).orElseThrow(RuntimeException::new);
        conferenceSection.addListener(conferenceUser);
        conferenceSectionRepository.save(conferenceSection);
        conferenceRepository.save(conference);
        return "Added listener";
    }

    List<Proposal> getAcceptedPapers() {
        return StreamSupport.stream(proposalRepository.findAll().spliterator(), false)
                .filter(Proposal::isAccepted)
                .collect(Collectors.toList());
    }

    @GetMapping(value="/getFee/{id}")
    public @ResponseBody float getFee(@PathVariable int id)
    {
        return conferenceRepository.findById(id).get().getFee();
    }
}
