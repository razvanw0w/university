package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.UserLoginDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Listener;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ListenerRepository;

import java.util.List;

@Controller
@RequestMapping("/listener")
@CrossOrigin(origins = "http://localhost:3000")
public class ListenerController {
    @Autowired
    private ListenerRepository listenerRepository;

    @GetMapping("/all")
    public @ResponseBody
    Iterable<Listener> getAlllisteners() {
        return listenerRepository.findAll();
    }

    @PostMapping("/add")
    public @ResponseBody
    String addlistener(@RequestParam Integer conferenceId, @RequestParam String name, @RequestParam String affiliation,
                       @RequestParam String email, @RequestParam String webpage, @RequestParam String username, @RequestParam String password) {
        Listener listener = new Listener(conferenceId, name, affiliation, email, webpage, username, password);
        listenerRepository.save(listener);
        return "Saved";
    }

    @CrossOrigin(origins = "http://localhost:3000")
    @GetMapping(path = "/login")
    public @ResponseBody
    UserLoginDTO login(@RequestParam String email, @RequestParam String password) {
        List<Listener> users = (List<Listener>) listenerRepository.findAll();
        boolean logged = false;
        Listener foundUser = null;
        for (Listener user : users) {
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
