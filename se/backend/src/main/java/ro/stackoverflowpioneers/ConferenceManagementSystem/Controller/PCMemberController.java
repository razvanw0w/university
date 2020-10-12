package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.UserLoginDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Chair;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ProgramCommitteeMember;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.PCMemberRepository;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Controller
@RequestMapping("/pcmembers")
@CrossOrigin(origins = "http://localhost:3000")
public class PCMemberController {
    @Autowired
    private PCMemberRepository pcMemberRepository;

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewPCMember(@RequestParam Integer conferenceId, @RequestParam String name, @RequestParam String affiliation,
                          @RequestParam String email, @RequestParam String webpage, @RequestParam String username,
                          @RequestParam String password) {
        ProgramCommitteeMember pcm = new ProgramCommitteeMember(conferenceId, name, affiliation, email, webpage, username, password);
        pcMemberRepository.save(pcm);
        return "Saved";
    }

    @GetMapping(path = "/all")
    public @ResponseBody Iterable<ProgramCommitteeMember> getAllPCMembers(){
        return pcMemberRepository.findAll();
    }

    @GetMapping(path = "/getall")
    public @ResponseBody
    Iterable<ProgramCommitteeMember> getPCMS(@RequestParam String conferenceId) {
        return StreamSupport.stream(pcMemberRepository.findAll().spliterator(), false)
                .filter(pc -> pc.getConferenceId() == Integer.parseInt(conferenceId))
                .collect(Collectors.toList());


    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/login")
    public @ResponseBody
    UserLoginDTO login(@RequestParam String email, @RequestParam String password) {
        List<ProgramCommitteeMember> users = (List<ProgramCommitteeMember>) pcMemberRepository.findAll();
        boolean logged = false;
        ProgramCommitteeMember foundUser = null;
        for (ProgramCommitteeMember user : users) {
            if (user.getPassword().equals(password) && user.getEmail().equals(email)) {
                foundUser = user;
                logged = true;
                break;
            }
        }
        if (!logged)
            return null;
        return new UserLoginDTO(foundUser.getId(), foundUser.getConferenceId());
    }
}
