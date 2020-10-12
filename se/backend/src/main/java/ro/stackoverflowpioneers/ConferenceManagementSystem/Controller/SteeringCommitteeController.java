package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.UserLoginDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.SteeringCommitteeMember;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.SteeringCommitteeMemberRepository;

import java.util.List;
import java.util.Optional;

@Controller
@RequestMapping("/steering")
@CrossOrigin(origins = "http://localhost:3000")
public class SteeringCommitteeController {
    @Autowired
    private SteeringCommitteeMemberRepository steeringCommitteeMemberRepository;

    @GetMapping(path = "/all")
    public @ResponseBody
    Iterable<SteeringCommitteeMember> getAllSteeringCommitteeMembers() {
        return steeringCommitteeMemberRepository.findAll();
    }

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewSteeringCommitteeMember(@RequestParam String name, @RequestParam String affiliation, @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password) {
        SteeringCommitteeMember steeringCommitteeMember = new SteeringCommitteeMember(name, affiliation, email, webpage, username, password);
        steeringCommitteeMemberRepository.save(steeringCommitteeMember);
        SteeringCommitteeMember steeringCommitteeMember1 = steeringCommitteeMemberRepository.findById(steeringCommitteeMember.getId()).orElseThrow(
                RuntimeException::new);
        System.out.println(steeringCommitteeMember1);
        System.out.println("Added steering commitee member");
        return "Steering Committee Member saved";
    }

    @PostMapping(path = "/update")
    public @ResponseBody
    String addNewSteeringCommitteeMember(@RequestParam int id, @RequestParam String name, @RequestParam String affiliation, @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password){
        Optional<SteeringCommitteeMember> opt = steeringCommitteeMemberRepository.findById(id);
        if (!opt.isPresent())
            return "The id doesn't exist!";
        SteeringCommitteeMember steeringCommitteeMember = new SteeringCommitteeMember(name, affiliation, email, webpage, username, password);
        steeringCommitteeMember.setId(id);
        steeringCommitteeMemberRepository.save(steeringCommitteeMember);
        return "Steering Committee Member updated!";
    }

    @PostMapping(path = "/delete")
    public @ResponseBody
    String addNewSteeringCommitteeMember(@RequestParam int id){
        Optional<SteeringCommitteeMember> opt = steeringCommitteeMemberRepository.findById(id);
        if (!opt.isPresent())
            return "The id doesn't exist!";
        steeringCommitteeMemberRepository.deleteById(id);
        return "Steering Committee Member deleted!";
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/login")
    public @ResponseBody
    UserLoginDTO login(@RequestParam String email, @RequestParam String password) {
        List<SteeringCommitteeMember> users = (List<SteeringCommitteeMember>) steeringCommitteeMemberRepository.findAll();
        boolean logged = false;
        SteeringCommitteeMember foundUser = null;
        for (SteeringCommitteeMember user : users) {
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
