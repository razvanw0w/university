package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ConferenceSection;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ProgramCommitteeMember;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ConferenceSectionRepository;

import java.util.Date;
import java.util.Optional;

@Controller
@RequestMapping("/conferencesections")
public class ConferenceSectionController {
    @Autowired
    private ConferenceSectionRepository conferenceSectionRepository;

    @PostMapping(path = "/add")
    public @ResponseBody
    String addNewConferenceSection(@RequestParam Integer noOfParticipants, @RequestParam Integer roomNumber, @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date startTime,
                                   @RequestParam @DateTimeFormat(pattern = "dd-MM-yyyy") Date endTime /*, @RequestParam ProgramCommitteeMember supervisor ,@RequestParam List<Author> speakers, @RequestParam List<ConferenceParticipants> listeners*/) {
        ConferenceSection conf = new ConferenceSection();
        conf.setNoOfParticipants(noOfParticipants);
        conf.setRoomNumber(roomNumber);
        conf.setStartTime(startTime);
        conf.setEndTime(endTime);
//        conf.setSupervisor(supervisor);
//        speakers.forEach(x-> conf.addSpeaker(x));
//        listener.forEach(x-> conf.addListener(x));
        conferenceSectionRepository.save(conf);
        return "Saved";
    }

    @PostMapping(path = "/update")
    public @ResponseBody
    String updateConferenceSection(@RequestParam Integer id,@RequestParam Integer noOfParticipants, @RequestParam Integer roomNumber, @RequestParam Date startTime,
                                   @RequestParam Date endTime ,@RequestParam ProgramCommitteeMember supervisor/*,@RequestParam List<Author> speakers, @RequestParam List<ConferenceParticipants> listeners*/) {
        Optional<ConferenceSection> opt = conferenceSectionRepository.findById(id);
        if(!opt.isPresent())
            return "That id doesn't exist!";
        ConferenceSection conf = new ConferenceSection();
        conf.setNoOfParticipants(noOfParticipants);
        conf.setRoomNumber(roomNumber);
        conf.setStartTime(startTime);
        conf.setEndTime(endTime);
//        conf.setSupervisor(supervisor);
//        speakers.forEach(x-> conf.addSpeaker(x));
//        listener.forEach(x-> conf.addListener(x));
        conf.setId(id);
        conferenceSectionRepository.save(conf);
        return "Updated";
    }

    @PostMapping(path = "/delete")
    public @ResponseBody
    String deleteConferenceSection(@RequestParam int id)
    {
        Optional<ConferenceSection> opt = conferenceSectionRepository.findById(id);
        if(!opt.isPresent())
            return "That id doesn't exist!";
        conferenceSectionRepository.deleteById(id);
        return "Deleted";
    }

    @GetMapping(path = "/all")
    public @ResponseBody Iterable<ConferenceSection> getAllConferenceSection(){
        return conferenceSectionRepository.findAll();
    }
}
