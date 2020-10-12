package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.UserLoginDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Chair;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ChairRepository;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Controller
@RequestMapping("/chairs")
@CrossOrigin(origins = "http://localhost:3000")
public class ChairController {
    @Autowired
    private ChairRepository chairRepository;

    @PostMapping(path = "/delete")
    public @ResponseBody
    String deleteChair(@RequestParam int id) {
        Optional<Chair> opt = chairRepository.findById(id);
        if (!opt.isPresent())
            return "That id doesn't exist!";
        chairRepository.deleteById(id);
        return "Deleted";
    }

    @GetMapping(path = "/all")
    public @ResponseBody
    Iterable<Chair> getAllChairs() {
        return chairRepository.findAll();
    }

    @GetMapping(path = "/getall")
    public @ResponseBody
    Iterable<Chair> getChairs(@RequestParam String conferenceId) {
        return StreamSupport.stream(chairRepository.findAll().spliterator(), false)
                .filter(c -> c.getConferenceId() == Integer.parseInt(conferenceId))
                .collect(Collectors.toList());


    }

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewChair(@RequestParam Integer conferenceId, @RequestParam String name, @RequestParam String affiliation,
                       @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password) {
        Chair chair = new Chair(conferenceId, name, affiliation, email, webpage, username, password);
        chairRepository.save(chair);
        return "Saved";
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/login")
    public @ResponseBody
    UserLoginDTO login(@RequestParam String email, @RequestParam String password) {
        List<Chair> users = (List<Chair>) chairRepository.findAll();
        boolean logged = false;
        Chair foundUser = null;
        for (Chair user : users) {
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
